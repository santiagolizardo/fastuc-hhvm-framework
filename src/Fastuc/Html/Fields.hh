<?hh // strict
namespace Fastuc\Html;

class Fields
{
	/**
	 * @var array
	 */
	protected $fields;

	public function __construct()
	{
		$this->fields = array();
	}

	public function addField( \Fastuc\Html\Field $field, $label = null )
	{
		if( null === $label )
		{
			$this->fields[] = array( 'input' => $field, 'label' => null );
		}
		elseif( is_string( $label ) )
		{
			if( $field instanceof \Fastuc\Html\Field\Check )
			{
				$labelClass = new \Fastuc\Html\AroundFieldLabel( $label, $field );
			}
			else
			{
				$labelClass = new \Fastuc\Html\BeforeFieldLabel( $label, $field );
			}

			$this->fields[] = array( 'input' => $field, 'label' => $labelClass );
		}
		else
		{
			$this->fields[] = array( 'input' => $field, 'label' => $label );
		}
	}

	public function addFields()
	{
		$args = func_get_args();
		foreach( $args as $arg )
		{
			$this->addField( $arg );
		}
	}

	/**
	 * Returns the field control by its index.
	 *
	 * @param integer $index
	 * @return \Fastuc\Html\Field
	 */
	public function getField( $index )
	{
		if( isset( $this->fields[ $index ] ) )
		{
			return $this->fields[ $index ]['input'];
		}

		return null;
	}

	/**
	 * Returns the fields added to this container.
	 *
	 * @return array
	 */
	public function getFields()
	{
		return $this->fields;
	}

	public function clearFields()
	{
		$this->fields = array();
	}

	public function fieldsToString()
	{
		$string = '';
		foreach( $this->fields as $field )
		{
			if( null !== $field['label'] )
			{
				// @todo Move the P tags out of here.
				$string .= '<p>' . strval( $field['label'] ) . '</p>' . PHP_EOL;
			}
			else
			{
				$string .= strval( $field['input'] ) . PHP_EOL;
			}
		}
		return $string;
	}

	public function __toString()
	{
		return $this->fieldsToString();
	}
}

