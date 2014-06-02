<?hh // strict
namespace Fastuc\Input;

/**
 * This class validates and transforms data (mostly coming from user input).
 */
class Handler
{
	/**
	 * @var array
	 */
	protected array $validationTypes;

	/**
	 * @var array
	 */
	protected array $transformationTypes;

	public function __construct()
	{
		$this->validationTypes = array
		(
			'min-length' => function( $value, $args = null ) { return strlen( $value ) >= $args; },			
			'max-length' => function( $value, $args = null ) { return strlen( $value ) <= $args; },			
			'min-value' => function( $value, $args = null ) { return $value >= $args; },
			'max-value' => function( $value, $args = null ) { return $value <= $args; },
			'empty' => function( $value, $args = null )
			{
				return empty( $value ) == $args;
			},
			'email' => function( $value )
			{
				return filter_var( $value, FILTER_VALIDATE_EMAIL ) !== false;
			},
			'regex' => function( $value, $args )
			{
				return preg_match( $args, $value ) > 0;
			},
		);

		$this->transformationTypes = array
		(
			'lowercase' => function( $value ) { return strtolower( $value ); },
			'uppercase' => function( $value ) { return strtoupper( $value ); },
			'sanitize' => function( $value )
			{
				return \Fastuc\Utils\Strings::sanitize( $value );
			},
			'transliterate' => function( $value )
			{
				return \Fastuc\Utils\Strings::transliterate( $value );
			},
			'truncate' => function( $value, $args = null )
			{
				return substr( $value, 0, $args );
			},
			'trim' => function( $value )
			{
				return trim( $value );
			},
			'striptags' => function( $value )
			{
				return strip_tags( $value );
			},
			'htmlentities' => function( $value )
			{
				return htmlspecialchars( $value );
			},
			'integer' => function( $value ) { return intval( $value ); },
			'float' => function( $value ) { return floatval( $value ); },
			'bool' => function( $value ) { return (bool)( $value ); },
			'string' => function( $value ) { return strval( $value ); },
		);
	}

	/**
	 * @return mixed Fallback value if the validation has not passed, or the transformed value otherwise.
	 */
	public function getValue( string $value, array $validations, mixed $fallback = null, array $transformations = array() ) : mixed
	{
		foreach( $validations as $k => $v )
		{
			$validationName = is_int( $k ) ? $v : $k;	
			if( !isset( $this->validationTypes[ $validationName ] ) )
			{
				trigger_error( 'Validation does not exist: ' . $validationName );
				continue;
			}

			$validationArgs = is_int( $k ) ? null : $v;
			if( false === $this->validationTypes[ $validationName ]( $value, $validationArgs ) )
			{
				return $fallback;
			}
		}

		$transformedValue = $value;

		foreach( $transformations as $k => $v )
		{
			$transformationName = is_int( $k ) ? $v : $k;
			if( !isset( $this->transformationTypes[ $transformationName ] ) )
			{
				trigger_error( 'Transformation does not exist: ' . $transformationName );
				continue;
			}

			$transformationArgs = is_int( $k ) ? null : $v;
			$transformedValue = $this->transformationTypes[ $transformationName ]( $transformedValue, $transformationArgs );
		}

		return $transformedValue;
	}

	public function getBool( string $value, array $validations = array(), $fallback = null, array $transformations = array() ) : bool
	{
		return $this->getValue( $value, $validations, $fallback, array_merge( $transformations, array( 'bool' ) ) );
	}

	public function getInt( string $value, array $validations = array(), $fallback = null, array $transformations = array() ) : int
	{
		return $this->getValue( $value, $validations, $fallback, array_merge( $transformations, array( 'integer' ) ) );
	}

	public function getFloat( string $value, array $validations = array(), $fallback = null, array $transformations = array() ) : float
	{
		return $this->getValue( $value, $validations, $fallback, array_merge( $transformations, array( 'float' ) ) );
	}

	public function getString( string $value, array $validations = array(), $fallback = null, array $transformations = array() ) : string
	{
		return $this->getValue( $value, $validations, $fallback, array_merge( $transformations, array( 'string' ) ) );
	}
}

