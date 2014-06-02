<?hh // strict
namespace Fastuc\Html;

class InputField extends \Fastuc\Html\Field
{
	protected $el;

	public function __construct( $type, $name, $value = null )
	{
		parent::__construct( $name );

		$this->el = $this->doc->createElement( 'input' );
		$this->el->setAttribute( 'type', $type );

		$this->setValue( $value );
	}

	/**
	 * @return string
	 */
	public function getType()
	{
		return $this->el->getAttribute( 'type' );
	}

	public function setReadonly( $readonly )
	{
		if( $readonly )
		{
			$this->el->setAttribute( 'readonly', 'readonly' );
		}
		else
		{
			$this->el->removeAttribute( 'readonly' );
		}
		return $this;
	}

	public function isReadonly()
	{
		return $this->el->hasAttribute( 'readonly' );
	 }

	public function setDisabled( $disabled )
	{
		if( $disabled )
		{
			$this->el->setAttribute( 'disabled', 'disabled' );
		}
		else
		{
			$this->el->removeAttribute( 'disabled' );
		}
		return $this;
	}

	public function isDisabled()
	{
		return $this->el->hasAttribute( 'disabled' );
	}

	public function __toString()
	{
		$this->el->setAttribute( 'id', $this->name );
		$this->el->setAttribute( 'name', $this->name );
		$this->el->setAttribute( 'value', $this->value );

		if( null !== $this->class )
		{
			$this->el->setAttribute( 'class', $this->class );
		}

		if( $this->isRequired() )
		{
			$this->el->setAttribute( 'required', 'required' );
		}
		if( $this->isAutofocus() )
		{
			$this->el->setAttribute( 'autofocus', 'autofocus' );
		}

		return $this->doc->saveXml( $this->el );
	}
}

